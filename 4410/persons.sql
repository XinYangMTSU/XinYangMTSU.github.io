-- DROP DATABASE IF EXISTS CSCI4410;
CREATE DATABASE IF NOT EXISTS CSCI4410;
USE CSCI4410;

DROP TABLE IF EXISTS Persons;

CREATE TABLE Persons (
    PersonID INT PRIMARY KEY,
    LastName VARCHAR(30) NOT NULL,
    FirstName VARCHAR(30) NOT NULL,
    Address VARCHAR(45),
    City VARCHAR(30)
);

INSERT INTO Persons (PersonID, LastName, FirstName, Address, City)
VALUES
    (1234, 'Lovelace', 'Ada', '1515 Bluebird', 'Magnolia'),
    (1235, 'Moreno', 'Antonio', '120 Hanover St.', 'Smyrna'),
    (1256, 'Roland', 'Mendel', '801 Kirch Road', 'Murfreesboro');
