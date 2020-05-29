package com.nhy.store.waiter.controller;

import com.nhy.store.waiter.model.Customer;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

import javax.validation.Valid;
import java.util.Objects;

@Controller
@RequestMapping("/")
public class testcontroller {
//    @GetMapping("/index")
//    public ModelAndView login(ModelAndView modelAndView) {
//        modelAndView.setViewName("index");
//        return modelAndView;
//    }

    @GetMapping("/login")
    public ModelAndView login(ModelAndView modelAndView){
        modelAndView.setViewName("login");
        return modelAndView;
    }

    @PostMapping("/login")
    public String login(ModelAndView modelAndView, @Valid Customer userVo, BindingResult bindingResult) {
        if (bindingResult.hasErrors()) {
            modelAndView.addObject("error", Objects.requireNonNull(bindingResult.getFieldError()).getDefaultMessage());
            modelAndView.setViewName("login");
            return "redirect:/z/1";
        }
        String userName = userVo.getName();
        String password = userVo.getPassword();

        if (!"admin".equals(userName)) {
            modelAndView.addObject("error", "无此用户！");
            modelAndView.setViewName("login");
            return "redirect:/z/1";
        }
        if (!"123456".equals(password)) {
            modelAndView.addObject("error", "密码错误！");
            modelAndView.setViewName("login");
            return "redirect:/z/1";
        }
        return "redirect:/z/1";
    }
}
