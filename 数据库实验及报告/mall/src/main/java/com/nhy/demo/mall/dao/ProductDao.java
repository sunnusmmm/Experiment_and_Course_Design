package com.nhy.demo.mall.dao;

import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import com.nhy.demo.mall.entity.Product;

import java.util.List;

public interface ProductDao extends JpaRepository<Product, Integer> {
    //根据类别查找商品
    List<Product> findByCsidIn(List<Integer> csids,Pageable pageable);
    //查找热门商品
    List<Product> findByIsHot(int isHot,Pageable pageable);
}
