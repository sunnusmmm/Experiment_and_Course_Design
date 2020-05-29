package com.nhy.store.waiter.controller;

import com.nhy.store.waiter.model.User;


import com.nhy.store.waiter.repository.UserRepository;
import com.nhy.store.waiter.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

import java.util.List;

@Controller
@RequestMapping("/index")
public class UserController {
    @Autowired
    private UserRepository userRepository;

    @Autowired
    private UserService userService;

    @GetMapping
    public String toIndex(Model model) {
        List<User> users = userRepository.findAll();
        model.addAttribute("users", users);
        return "/index";
    }

    @PostMapping(value = "/toindex")
    public ModelAndView loginEnd(User user) {

//        User user2 = userService.login(user);
        User user2 = new User("asd","1","1");
        if (user2 != null) {
            return new ModelAndView("redirect:/index", "loginUser", user2);
        }

        return new ModelAndView("login", "loginFail", "登录失败");
    }

    @GetMapping("delete/{id}")
    public String deleteUser(@PathVariable Long id) {
        userRepository.deleteById(id);
        return "redirect:/index";
    }

//    @GetMapping("/{id}")
//    public String getUser(Model model, @PathVariable Long id) {
//        User user = userRepository.findById(id).get();
//        model.addAttribute("one", user);
//        return "/userInfo";
//    }

    @PostMapping("/add")
    public String addUser(User user) {
        user.setBCryptPassword(user.getPassword());
        userRepository.save(user);
        System.out.println("保存了");
        return "redirect:/index";
    }

//    @GetMapping("/touserForm")
//    public String addUser() {
//        return "/userForm";
//    }
}
