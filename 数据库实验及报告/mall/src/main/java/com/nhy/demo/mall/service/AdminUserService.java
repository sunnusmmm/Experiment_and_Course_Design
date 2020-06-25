package com.nhy.demo.mall.service;

import org.springframework.data.domain.Example;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.http.HttpRequest;
import com.nhy.demo.mall.entity.AdminUser;

import javax.servlet.http.HttpServletRequest;
import java.util.List;

public interface AdminUserService {
    //根据id查询
    AdminUser findById(int id);
    //分页查询所有
    Page<AdminUser> findAll(Pageable pageable);
    //检查登录
    AdminUser checkLogin(HttpServletRequest request,String username, String pwd);

    void update(AdminUser adminUser);

    int create(AdminUser adminUser);

    void delById(int id);
}
