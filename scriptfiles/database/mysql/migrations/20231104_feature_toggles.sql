create table if not exists feature_toggles
(
    id          int auto_increment              primary key,
    toggle_key  varchar(128)                       not null,
    description mediumtext                         null,
    enabled     tinyint  default 0                 not null,
    created_at  datetime default CURRENT_TIMESTAMP not null,
    updated_at  datetime default CURRENT_TIMESTAMP not null on update CURRENT_TIMESTAMP,
    constraint feature_toggles_toggle_key_uindex
        unique (toggle_key)
);

