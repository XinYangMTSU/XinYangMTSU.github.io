USE CSCI4410;

-- Drop the Products table if it exists
DROP TABLE IF EXISTS Products;

-- Create the Products table with AUTO_INCREMENT and PRIMARY KEY
CREATE TABLE Products (
    ProductID INT(11) AUTO_INCREMENT PRIMARY KEY,
    ProductName VARCHAR(48),
    SupplierID INT(11),
    CategoryID INT(11),
    Unit VARCHAR(30),
    Price FLOAT(10,2)
);

-- Insert records into Products (no need to insert ProductID manually!)
INSERT INTO Products (ProductName, SupplierID, CategoryID, Unit, Price)
VALUES 
    ('Chais', 1, 1, '10 boxes x 20 bags', 18.00),
    ('Chang', 1, 1, '24-12 oz bottles', 19.00),
    ('Aniseed Syrup', 1, 2, '12-550 ml bottles', 10.00),
    ("Chef Anton's Cajun Seasoning", 2, 2, '48-6 oz jars', 22.00),
    ("Chef Anton's Gumbo Mix", 2, 2, '36 boxes', 21.35),
    ("Grandma's Boysenberry Spread", 3, 2, '12-8 oz jars', 25.00),
    ("Uncle Bob's Organic Dried Pears", 3, 7, '12-1 lb pkgs.', 30.00),
    ("Northwoods Cranberry Sauce", 3, 2, '12-12 oz jars', 40.00),
    ("Mishi Kobe Niku", 4, 6, '18-500 g pkgs.', 97.00),
    ("Ikura", 4, 8, '12-200 ml jars', 31.00);
