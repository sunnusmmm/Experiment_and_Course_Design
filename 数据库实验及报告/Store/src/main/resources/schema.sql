drop table t_coffee if exists;
drop table t_order if exists;
drop table t_order_coffee if exists;

create table t_coffee (
    id bigint auto_increment,
    create_time timestamp,
    update_time timestamp,
    type varchar(25),
    name varchar(25),
    price double,
    discount double,
    description varchar(255),
    primary key (id)
);

create table t_order (
    id bigint auto_increment,
    create_time timestamp,
    update_time timestamp,
    customer varchar(255),
    state integer not null,
    primary key (id)
);

create table t_order_coffee (
    coffee_order_id bigint not null,
    items_id bigint not null
);
create table t_user(
    id bigint auto_increment,
    username varchar(25),
    password varchar(25),
    primary key (id)
)

-- create table t_user_roles(
--     id bigint auto_increment,
--     rolename varchar(25),
--     primary key (id)
-- )