##  建表过程
CREATE TABLE User
(
Id int  primary key,
LoginState int,
Name varchar(255) NOT NULL,
Password varchar(255) NOT NULL,
Sex int,
Email varchar(255),
Telephone varchar(255),
Question varchar(255),
Answer varchar(255),
Description varchar(255),
LastLoginDate DATETIME NOT NULL
);

CREATE TABLE Friend
(
Id1 int references User (Id),
Id2 int references User (Id), 
Groupint int,
primary key(Id1,Id2)
);

CREATE TABLE ChatContent
(
Id1 int,
Id2 int, 
Time DATETIME,
Content text,
constraint s1 foreign key(Id1,Id2) references Friend(Id1,Id2)
);