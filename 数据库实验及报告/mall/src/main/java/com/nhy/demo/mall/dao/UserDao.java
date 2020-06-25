package com.nhy.demo.mall.dao;

import org.springframework.data.jpa.repository.JpaRepository;
import com.nhy.demo.mall.entity.User;

import java.util.List;

public interface UserDao extends JpaRepository<User, Integer> {
    //根据用户名、密码查询用户
    User findByUsernameAndPassword(String username, String password);
    //更据用户名查找用户
    List<User> findByUsername(String username);
}
