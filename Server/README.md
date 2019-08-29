##  建表过程
'''
CREATE TABLE User
(
Id int,
Name varchar(255),
Password varchar(255),
Sex int,
Email varchar(255),
Telephone varchar(255),
Question varchar(255),
Answer varchar(255),
Description varchar(255)
);

CREATE TABLE Friend
(
Id1 int,
Id2 int, 
Groupint int
);

CREATE TABLE ChatContent
(
Id1 int,
Id2 int, 
Content text
);
'''