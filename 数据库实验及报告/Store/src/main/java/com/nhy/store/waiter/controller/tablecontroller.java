package com.nhy.store.waiter.controller;

import com.nhy.store.waiter.model.People;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.servlet.ModelAndView;

import java.util.*;

@RestController
public class tablecontroller {
    @GetMapping("/")
    public People get() {
        return new People("1", "socks", "123456", new Date(), "GMT");
    }

    private List<People> peopleList = new ArrayList<>();

    {
        peopleList.add(new People("1", "socks1", "111111", new Date(), "GMT1"));
        peopleList.add(new People("2", "socks2", "514730", new Date(), "GMT2"));
        peopleList.add(new People("3", "socks3", "112233", new Date(), "GMT3"));
        peopleList.add(new People("4", "socks4", "147892", new Date(), "GMT4"));
    }

    @GetMapping("z")
    public ModelAndView index() {
        return new ModelAndView("user/user", "userList", peopleList);
    }

    @GetMapping("z/{id}")
    public ModelAndView index(@PathVariable("id") int id) {
        ModelAndView mv = new ModelAndView("Commodity");

        Map user = new HashMap();
        user.put("name", "姓名");
        user.put("age", "年龄");
        user.put("sex", "性别");
        user.put("birthday", "生日");
        user.put("phonenumber", "手机");
        System.out.println(peopleList.get(id));

        People p = new People("1", "socks", "123456", new Date(), "GMT");

        mv.addObject("uid","1");
        mv.addObject("name","Mike");
        mv.addObject("p", p);
        mv.addObject("userList", peopleList);
        mv.addObject("map", user);
        mv.addObject("people", peopleList.get(id));
        mv.addObject("userList", peopleList);

        return mv;
    }
}
