package com.nhy.demo.mall.dao;

import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import com.nhy.demo.mall.entity.Classification;

import java.util.List;

public interface ClassificationDao extends JpaRepository<Classification, Integer> {
    //根据类别查找
    List<Classification> findByType(int type);
    Page<Classification> findByType(int type, Pageable pageable);
    //根据ID查找
    List<Classification> findById(int cid);
}
