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
    private Integer id;
    /**
     * 用户名
     */
    @Column
    private String username;
    /**
     * 密码
     */
    @Column
    private String password;
    /**
     * 姓名
     */
    @Column
    private String name;
    /**
     * 邮件
     */
    @Column
    private String email;
    /**
     * 电话
     */
    @Column
    private String phone;
    /**
     * 地址
     */
    @Column
    private String addr;
}