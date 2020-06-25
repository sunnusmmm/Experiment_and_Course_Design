package com.nhy.demo.mall.service;

import org.springframework.data.domain.Example;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import com.nhy.demo.mall.entity.Classification;

import java.util.List;

public interface ClassificationService {
    //根据id查询
    Classification findById(int id);

    //按分类查询所有
    List<Classification> findAll(int type);

    //按分类查询所有
    Page<Classification> findAll(int type,Pageable pageable);

    void update(Classification Classification);

    int create(Classification Classification);

    void delById(int id);
}
