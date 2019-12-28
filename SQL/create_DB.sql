DROP DATABASE IF EXISTS zoo_management;

CREATE DATABASE zoo_management;
USE zoo_management;

CREATE TABLE user
(
  user_ID INT NOT NULL,
  user_name VARCHAR(250) NOT NULL,
  birth_date DATE NOT NULL,
  user_password VARCHAR(250) NOT NULL,
  email VARCHAR(250) NOT NULL,
  PRIMARY KEY (user_ID)
);

CREATE TABLE employee
(
  user_ID INT NOT NULL,
  begin_contract DATE NOT NULL,
  end_contract DATE,
  phone BIGINT NOT NULL,
  PRIMARY KEY (user_ID),
  FOREIGN KEY (user_ID) REFERENCES user(user_ID)
);

CREATE TABLE manager
(
  user_ID INT NOT NULL,
  PRIMARY KEY (user_ID),
  FOREIGN KEY (user_ID) REFERENCES employee(user_ID)
);

CREATE TABLE keeper
(
  user_ID INT NOT NULL,
  PRIMARY KEY (user_ID),
  FOREIGN KEY (user_ID) REFERENCES employee(user_ID)
);

CREATE TABLE veterinarian
(
  user_ID INT NOT NULL,
  PRIMARY KEY (user_ID),
  FOREIGN KEY (user_ID) REFERENCES employee(user_ID)
);

CREATE TABLE visitor
(
  user_ID INT NOT NULL,
  PRIMARY KEY (user_ID),
  FOREIGN KEY (user_ID) REFERENCES user(user_ID)
);

CREATE TABLE stock
(
  stock_ID INT NOT NULL,
  stock_type VARCHAR(250) NOT NULL,
  stock_description VARCHAR(250) NOT NULL,
  initial_quantity FLOAT NOT NULL,
  unit_value FLOAT NOT NULL,
  PRIMARY KEY (stock_ID)
);

CREATE TABLE animal
(
  animal_ID INT NOT NULL,
  animal_name VARCHAR(250) NOT NULL,
  gender VARCHAR(250) NOT NULL,
  birth_date DATE NOT NULL,
  wild_date DATE,
  origin VARCHAR(250) NOT NULL,
  photo VARCHAR(250),
  PRIMARY KEY (animal_ID)
);

CREATE TABLE consume
(
  animal_ID INT NOT NULL,
  stock_ID INT NOT NULL,
  consume_date DATE NOT NULL,
  consume_quantity FLOAT NOT NULL,
  PRIMARY KEY (stock_ID, animal_ID),
  FOREIGN KEY (stock_ID) REFERENCES stock(stock_ID),
  FOREIGN KEY (animal_ID) REFERENCES animal(animal_ID)
);

CREATE TABLE godfather
(
  animal_ID INT NOT NULL,
  user_ID INT NOT NULL,
  status VARCHAR(250) NOT NULL,
  request_date DATE NOT NULL,
  fee FLOAT NOT NULL,
  start_date DATE,
  ending_date DATE,
  PRIMARY KEY (user_ID, animal_ID),
  FOREIGN KEY (user_ID) REFERENCES visitor(user_ID),
  FOREIGN KEY (animal_ID) REFERENCES animal(animal_ID)
);

CREATE TABLE species
(
  species_ID INT NOT NULL,
  species_name VARCHAR(250) NOT NULL,
  conservation_status VARCHAR(250) NOT NULL,
  base_fee FLOAT NOT NULL,
  phylum VARCHAR(250) NOT NULL,
  class VARCHAR(250) NOT NULL,
  species_order VARCHAR(250) NOT NULL,
  suborder VARCHAR(250),
  family VARCHAR(250) NOT NULL,
  subfamily VARCHAR(250),
  genus VARCHAR(250) NOT NULL,
  scientific_name VARCHAR(250) NOT NULL,
  PRIMARY KEY (species_ID)
);

CREATE TABLE medical_record
(
  record_ID INT NOT NULL,
  user_ID INT NOT NULL,
  animal_ID INT NOT NULL,
  record_type VARCHAR(250) NOT NULL,
  record_description VARCHAR(250) NOT NULL,
  prescription VARCHAR(250),
  appointment_date DATE NOT NULL,
  PRIMARY KEY (record_ID, user_ID, animal_ID),
  FOREIGN KEY (user_ID) REFERENCES veterinarian(user_ID),
  FOREIGN KEY (animal_ID) REFERENCES animal(animal_ID)
);

CREATE TABLE zones
(
  zones_ID INT NOT NULL,
  area FLOAT NOT NULL,
  biome VARCHAR(250) NOT NULL,
  PRIMARY KEY (zones_ID)
);

CREATE TABLE lives
(
  animal_ID INT NOT NULL,
  zones_ID INT NOT NULL,
  PRIMARY KEY (animal_ID, zones_ID),
  FOREIGN KEY (animal_ID) REFERENCES animal(animal_ID),
  FOREIGN KEY (zones_ID) REFERENCES zones(zones_ID)
);

CREATE TABLE tasks
(
  task_ID INT NOT NULL,
  task_type VARCHAR(250) NOT NULL,
  task_description VARCHAR(250) NOT NULL,
  PRIMARY KEY (task_ID)
);

CREATE TABLE responsible
(
  user_ID INT NOT NULL,
  stock_ID INT NOT NULL,
  PRIMARY KEY (user_ID, stock_ID),
  FOREIGN KEY (user_ID) REFERENCES manager(user_ID),
  FOREIGN KEY (stock_ID) REFERENCES stock(stock_ID)
);

CREATE TABLE orders
(
  user_ID INT NOT NULL,
  stock_ID INT NOT NULL,
  order_date DATE NOT NULL,
  order_quantity FLOAT NOT NULL,
  PRIMARY KEY (user_ID, stock_ID, order_date),
  FOREIGN KEY (user_ID) REFERENCES manager(user_ID),
  FOREIGN KEY (stock_ID) REFERENCES stock(stock_ID)
);

CREATE TABLE belongs
(
  animal_ID INT NOT NULL,
  species_ID INT NOT NULL,
  PRIMARY KEY (species_ID, animal_ID),
  FOREIGN KEY (species_ID) REFERENCES species(species_ID),
  FOREIGN KEY (animal_ID) REFERENCES animal(animal_ID)
);

CREATE TABLE schedule_keeper
(
  task_ID INT NOT NULL,
  zones_ID INT NOT NULL,
  schedule_date DATE NOT NULL,
  PRIMARY KEY (zones_ID, task_ID, schedule_date),
  FOREIGN KEY (zones_ID) REFERENCES zones(zones_ID),
  FOREIGN KEY (task_ID) REFERENCES tasks(task_ID)
);

CREATE TABLE assigned
(
  user_ID INT NOT NULL,
  zones_ID INT NOT NULL,
  task_ID INT NOT NULL,
  schedule_date DATE NOT NULL,
  PRIMARY KEY (zones_ID, task_ID, user_ID, schedule_date),
  FOREIGN KEY (zones_ID, task_ID, schedule_date) REFERENCES schedule_keeper(zones_ID, task_ID, schedule_date),
  FOREIGN KEY (user_ID) REFERENCES keeper(user_ID)
);
