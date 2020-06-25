package com.nhy.demo.mall.service.impl;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;
import com.nhy.demo.mall.dao.UserDao;
import com.nhy.demo.mall.entity.User;
import com.nhy.demo.mall.service.UserService;

import java.util.List;

@Service
public class UserServiceImpl implements UserService {
    @Autowired
    private UserDao userDao;

    @Override
    public User findById(int id) {
        return userDao.getOne(id);
    }

    @Override
    public Page<User> findAll(Pageable pageable) {
        return userDao.findAll(pageable);
    }

    @Override
    public void update(User user) {
        userDao.save(user);
    }

    @Override
    public int create(User user) {
        return userDao.save(user).getId();
    }

    @Override
    public void delById(int id) {
        userDao.deleteById(id);
    }

    @Override
    public List<User> findByUsername(String username) {
        return userDao.findByUsername(username);
    }

    @Override
    public User checkLogin(String username, String password) {
        return userDao.findByUsernameAndPassword(username, password);
    }
}