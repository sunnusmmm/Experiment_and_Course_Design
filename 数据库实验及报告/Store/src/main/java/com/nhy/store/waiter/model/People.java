package com.nhy.store.waiter.model;


import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Date;

@Data
@NoArgsConstructor
@AllArgsConstructor
@Builder
public class People {
    String Id;
    String name;
    String password;
    Date createTime;
    String timezone;
}
