package com.nhy.demo.mall.dao;

import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import com.nhy.demo.mall.entity.Classification;

import java.util.List;

public interface ClassificationDao extends JpaRepository<Classification, Integer> {
    List<Classification> findByType(int type);

    Page<Classification> findByType(int type, Pageable pageable);

    List<Classification> findById(int cid);
}
