-- Drop the database if it exists
DROP DATABASE IF EXISTS CSCI4410;

-- Create the database if it does not exist
CREATE DATABASE IF NOT EXISTS CSCI4410;
USE CSCI4410;

-- Drop the Customers table if it exists
DROP TABLE IF EXISTS Customers;

-- Create the Customers table with CustomerID as AUTO_INCREMENT and PRIMARY KEY
CREATE TABLE Customers (
    CustomerID INT(8) AUTO_INCREMENT PRIMARY KEY,
    CustomerName VARCHAR(30),
    ContactName VARCHAR(30),
    Address VARCHAR(45),
    City VARCHAR(30),
    PostalCod VARCHAR(30),
    Country VARCHAR(30)
);

-- Insert records into Customers (no need to insert CustomerID manually!)
INSERT INTO Customers (CustomerName, ContactName, Address, City, PostalCod, Country)
VALUES 
    ('Alfreds Futterkiste','Maria Anders',NULL,'Berlin','12209','Germany'),
    ('Ana Trujillo','Ana Trujillo','Avda. Constitución 2222','México D.F.','05021','Mexico'),
    ('Antonio Moreno','Antonio Moreno','Mataderos 2312','México D.F.','05023','Mexico'),
    ('Around the Horn','Thomas Hardy','120 Hanover Sq.','London','WA1 1DP','UK'),
    ('Berglunds snabbköp','Christina Berglund','Berguvsvägen 8','Luleå','S-958 22','Sweden'),
    ('Blauer See Delikatessen','Hanna Moos','Forsterstr. 57','Mannheim','68306','Germany'),
    ('Blondel père et fils','Frédérique Citeaux','24, place Kléber','Strasbourg','67000','France'),
    ('Bólido Comidas preparadas','Martín Sommer','C/ Araquil, 67','Madrid','28023','Spain'),
    ('Bon app','Laurence Lebihans','12, rue des Bouchers','Marseille','13008','France'),
    ('Bottom-Dollar Marketse','Elizabeth Lincoln','23 Tsawassen Blvd.','Tsawassen','T2F 8M4','Canada'),
    ("B's Beverages",'Victoria Ashworth','Fauntleroy Circus','London','EC2 5NT','UK'),
    ('Cactus Comidas para llevar','Patricio Simpson','Cerrito 333','Buenos Aires','1010','Argentina'),
    ('Centro Moctezuma','Francisco Chang','de Granada 9993','México D.F.','05022','Mexico'),
    ('Chop-suey Chinese','Yang Wang','Hauptstr. 29','Bern','3012','Switzerland'),
    ('Comércio Mineiro','Pedro Afonso','Av. dos Lusíadas, 23','São Paulo','05432-043','Brazil'),
    ('Consolidated Holdings','Elizabeth Brown','Berkeley Gardens 12 Brewery','London','WX1 6LT','UK'),
    ('Drachenblut Delikatessend','Sven Ottlieb','Walserweg 21','Aachen','52066','Germany'),
    ('Du monde entier','Janine Labrune','67, rue des Cinquante Otages','Nantes','44000','France'),
    ('Eastern Connection','Ann Devon','35 King George','London','WX3 6FW','UK'),
    ('Ernst Handel','Roland Mendel','Kirchgasse 6','Graz','8010','Austria');
