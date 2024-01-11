USE CSCI4410;

DROP TABLE IF EXISTS Products;

CREATE TABLE Products(
	ProductID INT(30),
	ProductName VARCHAR(48),
	SupplierID INT(30),
	CategoryID INT(30),
	Unit VARCHAR(30),
	Price FLOAT(30)
);

INSERT INTO Products
VALUES (1,'Chais',1,1,'10 boxes x 20 bags',18),
       (2,'Chang',1,1 ,'24-12 oz bottles',19),
       (3,'Aniseed Syrup',1,2,'12-550 ml bottles',10),
       (4,"Chef Anton's Cajun Seasoning",2,2,'48-6 oz jars',22),
       (5,"Chef Anton's Gumbo Mix",2,2,"36 boxes",21.35),
       (6,"Grandma's Boysenberry Spread",3,2,"12-8 oz jars",25),
       (7,"Uncle Bob's Organic Dried Pears",3,7,"12-1 lb pkgs.",30),
       (8,"Northwoods Cranberry Sauce",3,2,"12-12 oz jars",40),
       (9,"Mishi Kobe Niku",4,6,"18-500 g pkgs.",97),
       (10,"Ikura",4,8,"12-200 ml jars", 31);





