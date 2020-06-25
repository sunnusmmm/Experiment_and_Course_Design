package com.nhy.demo.mall.dao;

import org.springframework.data.jpa.repository.JpaRepository;
import com.nhy.demo.mall.entity.AdminUser;

public interface AdminUserDao extends JpaRepository<AdminUser, Integer> {
    //根据账号、密码查找
    AdminUser findByUsernameAndPassword(String username, String pwd);
}
