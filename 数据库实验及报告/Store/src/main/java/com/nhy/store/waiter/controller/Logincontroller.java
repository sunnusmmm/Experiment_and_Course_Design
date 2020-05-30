package com.nhy.store.waiter.controller;

import com.nhy.store.waiter.model.UserRole;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.servlet.ModelAndView;

import java.util.*;

@Controller
public class Logincontroller {
    @RequestMapping("/")
    public String index() {
        System.out.println("in======>index");
        return "redirect:/goods/";
    }
    @GetMapping("/test")
    public String get() {
        return "index";
    }
//
//    private List<UserRole> userRoleList = new ArrayList<>();
//
//    {
//        userRoleList.add(new UserRole("1", "socks1", "111111", new Date(), "GMT1"));
//        userRoleList.add(new UserRole("2", "socks2", "514730", new Date(), "GMT2"));
//        userRoleList.add(new UserRole("3", "socks3", "112233", new Date(), "GMT3"));
//        userRoleList.add(new UserRole("4", "socks4", "147892", new Date(), "GMT4"));
//    }
//
//    @GetMapping("z")
//    public ModelAndView index() {
//        return new ModelAndView("user/user", "userList", userRoleList);
//    }
//
//    @GetMapping("z/{id}")
//    public ModelAndView index(@PathVariable("id") int id) {
//        ModelAndView mv = new ModelAndView("Commodity");
//
//        Map user = new HashMap();
//        user.put("name", "姓名");
//        user.put("age", "年龄");
//        user.put("sex", "性别");
//        user.put("birthday", "生日");
//        user.put("phonenumber", "手机");
//        System.out.println(userRoleList.get(id));
//
//        UserRole p = new UserRole("1", "socks", "123456", new Date(), "GMT");
//
//        mv.addObject("uid","1");
//        mv.addObject("name","Mike");
//        mv.addObject("p", p);
//        mv.addObject("userList", userRoleList);
//        mv.addObject("map", user);
//        mv.addObject("people", userRoleList.get(id));
//        mv.addObject("userList", userRoleList);
//
//        return mv;
//    }
}
