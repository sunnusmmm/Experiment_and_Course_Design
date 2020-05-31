package com.nhy.store.waiter.service;


import com.nhy.store.waiter.model.User;
import com.nhy.store.waiter.repository.UserRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

@Service
public class UserServiceDetil implements UserDetailsService {
    static Logger log = LoggerFactory.getLogger(UserServiceDetil.class);
    @Autowired
    UserRepository userRepository;

    @Override
    public UserDetails loadUserByUsername(String userName) throws UsernameNotFoundException {
        log.info("param--userName===>" + userName);
        User user = userRepository.findByUserName(userName);
        if (user == null) {
            log.info("user===>" + null);
            throw new UsernameNotFoundException("用户名不存在");
        }
        log.info("userName===>" + user.getUsername());
        log.info("userPass===>" + user.getPassword());
        return user;
    }

    public boolean regUser(User user){
        userRepository.save(user);
        return true;
    }
}
