package com.nhy.demo.mall.entity;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.persistence.*;
import java.io.Serializable;

/**
 * 分类
 */
@Entity
@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
@Table(name = "classification")
public class Classification implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column
    private Integer id;
    /**
     * 分类名称
     */
    @Column
    private String cname;
    /**
     * 类型 1一级分类 2二级分类
     */
    @Column
    private Integer type;
}