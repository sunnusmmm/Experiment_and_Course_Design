package com.nhy.demo.mall.service;

import org.springframework.data.domain.Example;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import com.nhy.demo.mall.entity.User;

import java.util.List;

public interface UserService {
    //根据id查询
    User findById(int id);
    //分页查询所有
    Page<User> findAll(Pageable pageable);
    //根据用户名查询
    List<User> findByUsername(String username);
    //登陆验证
    User checkLogin(String username,String password);

    void update(User user);

    int create(User user);

    void delById(int id);
}
