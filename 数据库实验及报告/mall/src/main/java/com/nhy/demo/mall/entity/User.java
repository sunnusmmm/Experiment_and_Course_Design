package com.nhy.demo.mall.entity;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
@Table(name = "user")
public class User implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column
    private Integer id;//ID
    @Column
    private String username;//用户名
    @Column
    private String password;//密码
    @Column
    private String name;//姓名
    @Column
    private String email;//邮箱
    @Column
    private String phone;//电话
    @Column
    private String addr;//地址
}