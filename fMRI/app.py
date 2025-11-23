"""
fMRI Autism Analysis Pipeline - Complete Full-Stack Application
Backend: Flask API + Frontend: HTML/JavaScript in single directory
Run: python app.py
Access: http://localhost:5000
"""

from flask import Flask, jsonify, request, send_from_directory
from flask_cors import CORS
import numpy as np
import json
import os
from nilearn.connectome import ConnectivityMeasure
from nilearn.datasets import fetch_abide_pcp
from sklearn.svm import SVC
from sklearn.model_selection import StratifiedKFold, cross_validate
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score, f1_score, confusion_matrix, recall_score
import warnings
warnings.filterwarnings('ignore')

app = Flask(__name__, static_folder='.', static_url_path='')
CORS(app)

# Global variables to store data
dataset_cache = {
    'data': None,
    'X': None,
    'y': None,
    'scaler': None,
    'status': 'idle'
}

# ============= STATIC FILES =============
@app.route('/')
def serve_index():
    """Serve the main HTML file"""
    return send_from_directory('.', 'index.html')

# ============= API ENDPOINTS =============

@app.route('/api/health', methods=['GET'])
def health_check():
    """Health check endpoint"""
    return jsonify({
        'status': 'ok',
        'dataset_loaded': dataset_cache['data'] is not None,
        'connectivity_computed': dataset_cache['X'] is not None
    })

@app.route('/api/load-dataset', methods=['POST'])
def load_dataset():
    """Download and load quality-controlled ABIDE dataset"""
    try:
        dataset_cache['status'] = 'loading'
        print("Downloading ABIDE dataset...")
        
        abide_data = fetch_abide_pcp(
            derivatives=["rois_cc400"],
            pipeline="cpac",
            band_pass_filtering=True,
            global_signal_regression=True,
            quality_checked=True
        )
        
        dataset_cache['data'] = abide_data
        dataset_cache['status'] = 'loaded'
        
        total_subjects = len(abide_data.rois_cc400)
        autism_count = sum(1 for i in range(total_subjects) 
                          if abide_data.phenotypic.iloc[i]['DX_GROUP'] == 1)
        control_count = total_subjects - autism_count
        
        print(f"✓ Loaded {total_subjects} subjects (Autism: {autism_count}, Control: {control_count})")
        
        return jsonify({
            'success': True,
            'message': 'Quality-controlled ABIDE dataset loaded successfully!',
            'total_subjects': total_subjects,
            'autism_cases': autism_count,
            'control_cases': control_count
        })
    except Exception as e:
        dataset_cache['status'] = 'error'
        print(f"Error loading dataset: {e}")
        return jsonify({'success': False, 'error': str(e)}), 500

@app.route('/api/time-series', methods=['POST'])
def get_time_series():
    """Extract time series from a specific voxel/ROI"""
    try:
        data = request.json
        subject_idx = data.get('subject_index', 0)
        roi_idx = data.get('roi_index', 0)
        
        if dataset_cache['data'] is None:
            return jsonify({'success': False, 'error': 'Dataset not loaded'}), 400
        
        abide_data = dataset_cache['data']
        time_series_data = np.asarray(abide_data.rois_cc400[subject_idx])
        
        if roi_idx >= time_series_data.shape[1]:
            roi_idx = 0
        
        roi_ts = time_series_data[:, roi_idx]
        roi_ts_norm = (roi_ts - roi_ts.mean()) / (roi_ts.std() + 1e-6)
        
        return jsonify({
            'success': True,
            'time_series': roi_ts_norm.tolist(),
            'timestamps': list(range(len(roi_ts))),
            'mean': float(roi_ts.mean()),
            'std': float(roi_ts.std()),
            'roi_index': roi_idx,
            'subject_index': subject_idx,
            'n_timepoints': len(roi_ts)
        })
    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'success': False, 'error': str(e)}), 500

@app.route('/api/calculate-connectivity', methods=['POST'])
def calculate_connectivity():
    """Compute functional connectivity for all subjects"""
    try:
        data = request.json
        sample_size = data.get('sample_size', 50)
        
        if dataset_cache['data'] is None:
            return jsonify({'success': False, 'error': 'Dataset not loaded'}), 400
        
        dataset_cache['status'] = 'computing_connectivity'
        print(f"Computing connectivity for {sample_size} subjects...")
        
        abide_data = dataset_cache['data']
        conn_measure = ConnectivityMeasure(kind='correlation')
        
        X_conn = []
        y_labels = []
        valid_subjects = 0
        
        for idx in range(min(sample_size, len(abide_data.rois_cc400))):
            time_series = np.asarray(abide_data.rois_cc400[idx])
            
            if np.isnan(time_series).any():
                continue
            
            try:
                dx_group = abide_data.phenotypic.iloc[idx]['DX_GROUP']
                label = 0 if dx_group == 2 else 1
                
                conn_matrix = conn_measure.fit_transform([time_series])[0]
                conn_vector = conn_matrix[np.triu_indices_from(conn_matrix, k=1)]
                
                X_conn.append(conn_vector)
                y_labels.append(label)
                valid_subjects += 1
            except Exception as e:
                continue
        
        if len(X_conn) == 0:
            return jsonify({'success': False, 'error': 'No valid subjects processed'}), 500
        
        X_conn = np.array(X_conn)
        y_labels = np.array(y_labels)
        
        dataset_cache['X'] = X_conn
        dataset_cache['y'] = y_labels
        dataset_cache['status'] = 'ready_for_training'
        
        print(f"✓ Processed {len(X_conn)} subjects")
        print(f"  Matrix shape: {X_conn.shape}")
        print(f"  Class distribution: Control={np.sum(y_labels == 0)}, Autism={np.sum(y_labels == 1)}")
        
        return jsonify({
            'success': True,
            'message': f'Computed connectivity for {len(X_conn)} subjects',
            'n_subjects': len(X_conn),
            'n_features': X_conn.shape[1],
            'class_distribution': {
                'control': int(np.sum(y_labels == 0)),
                'autism': int(np.sum(y_labels == 1))
            },
            'matrix_stats': {
                'mean_corr': float(X_conn.mean()),
                'std_corr': float(X_conn.std()),
                'min_corr': float(X_conn.min()),
                'max_corr': float(X_conn.max())
            }
        })
    except Exception as e:
        dataset_cache['status'] = 'error'
        print(f"Error: {e}")
        return jsonify({'success': False, 'error': str(e)}), 500

@app.route('/api/train-svm', methods=['POST'])
def train_svm():
    """Train SVM classifier with 5-fold cross-validation"""
    try:
        if dataset_cache['X'] is None or dataset_cache['y'] is None:
            return jsonify({'success': False, 'error': 'Connectivity data not computed yet'}), 400
        
        dataset_cache['status'] = 'training_svm'
        print("Training SVM classifier...")
        
        X = dataset_cache['X']
        y = dataset_cache['y']
        
        scaler = StandardScaler()
        X_scaled = scaler.fit_transform(X)
        dataset_cache['scaler'] = scaler
        
        skf = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)
        svm = SVC(kernel='rbf', C=10, class_weight='balanced', random_state=42)
        
        scoring = {
            'accuracy': 'accuracy',
            'precision': 'precision_binary',
            'recall': 'recall_binary',
            'f1': 'f1_binary'
        }
        
        cv_results = cross_validate(svm, X_scaled, y, cv=skf, scoring=scoring, return_train_score=False)
        
        svm.fit(X_scaled, y)
        y_pred = svm.predict(X_scaled)
        
        accuracy = accuracy_score(y, y_pred)
        sensitivity = recall_score(y, y_pred, pos_label=1)
        specificity = recall_score(y, y_pred, pos_label=0)
        f1 = f1_score(y, y_pred)
        
        tn, fp, fn, tp = confusion_matrix(y, y_pred).ravel()
        
        dataset_cache['status'] = 'trained'
        
        print(f"✓ SVM Training Complete")
        print(f"  Accuracy: {accuracy:.4f}")
        print(f"  Sensitivity: {sensitivity:.4f}")
        print(f"  Specificity: {specificity:.4f}")
        print(f"  F1 Score: {f1:.4f}")
        print(f"  CV Accuracy: {cv_results['test_accuracy'].mean():.4f} ± {cv_results['test_accuracy'].std():.4f}")
        
        return jsonify({
            'success': True,
            'message': 'SVM training completed',
            'overall_metrics': {
                'accuracy': float(accuracy),
                'sensitivity': float(sensitivity),
                'specificity': float(specificity),
                'f1_score': float(f1)
            },
            'cross_validation': {
                'accuracy_scores': cv_results['test_accuracy'].tolist(),
                'accuracy_mean': float(cv_results['test_accuracy'].mean()),
                'accuracy_std': float(cv_results['test_accuracy'].std()),
                'f1_scores': cv_results['test_f1'].tolist(),
                'f1_mean': float(cv_results['test_f1'].mean())
            },
            'confusion_matrix': {
                'true_negatives': int(tn),
                'false_positives': int(fp),
                'false_negatives': int(fn),
                'true_positives': int(tp)
            },
            'sample_count': {
                'total': int(len(y)),
                'autism': int(np.sum(y == 1)),
                'control': int(np.sum(y == 0))
            }
        })
    except Exception as e:
        dataset_cache['status'] = 'error'
        print(f"Error: {e}")
        return jsonify({'success': False, 'error': str(e)}), 500

if __name__ == '__main__':
    print("\n" + "="*60)
    print("fMRI Autism Analysis Pipeline - Full Stack Application")
    print("="*60)
    print("\n✓ Backend API starting...")
    print("✓ Frontend available at: http://localhost:5000")
    print("\nAPI Endpoints:")
    print("  GET  /api/health")
    print("  POST /api/load-dataset")
    print("  POST /api/time-series")
    print("  POST /api/calculate-connectivity")
    print("  POST /api/train-svm")
    print("\nPress Ctrl+C to stop\n")
    
    app.run(debug=True, host='0.0.0.0', port=5000, use_reloader=False)
