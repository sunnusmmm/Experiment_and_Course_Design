package com.nhy.demo.mall.controller.admin;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import com.nhy.demo.mall.entity.AdminUser;
import com.nhy.demo.mall.service.AdminUserService;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@Controller
@RequestMapping("/admin")
public class AdminController {
    @Autowired
    private AdminUserService adminUserService;

    //访问首页
    @RequestMapping("/toIndex.html")
    public String toIndex() {
        return "admin/index";
    }

    //访问登录页面
    @RequestMapping("/toLogin.html")
    public String toLogin() {
        return "admin/login";
    }

    //登录请求
    //@ResponseBody
    @RequestMapping(method = RequestMethod.POST, value = "/login.do")
    public void login(String username, String password, HttpServletRequest request, HttpServletResponse response) throws IOException {
        AdminUser adminUser = adminUserService.checkLogin(request, username, password);
        response.sendRedirect("/mall/admin/toIndex.html");
    }

    //注销
    @RequestMapping("/logout.do")
    public void logout(HttpServletRequest request, HttpServletResponse response) throws IOException {
        request.getSession().removeAttribute("login_user");
        response.sendRedirect("toLogin.html");
    }
}
