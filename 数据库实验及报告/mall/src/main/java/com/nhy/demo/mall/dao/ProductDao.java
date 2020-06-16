package com.nhy.demo.mall.dao;

import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import com.nhy.demo.mall.entity.Product;

import java.util.List;

public interface ProductDao extends JpaRepository<Product, Integer> {
    /**
     * 通过二级分类查找商品列表
     *
     * @param csid
     * @param pageable
     * @return
     */
    List<Product> findByCsid(int csid, Pageable pageable);

    List<Product> findByCsidIn(List<Integer> csids,Pageable pageable);

    /**
     * 查找热门商品
     * @param isHot
     * @param pageable
     * @return
     */
    List<Product> findByIsHot(int isHot,Pageable pageable);

    /**
     * 查询最新商品，最近上新的20个商品
     * @param pageable
     * @return
     */
    @Query(value = "SELECT * FROM (SELECT  * FROM product ORDER BY pdate DESC limit 0,24) a /*#pageable*/",nativeQuery = true)
    List<Product> findNew(Pageable pageable);
}
