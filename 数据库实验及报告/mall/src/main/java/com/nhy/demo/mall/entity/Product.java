package com.nhy.demo.mall.entity;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Date;
@Entity
@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
@Table(name = "product")
@JsonIgnoreProperties({ "handler","hibernateLazyInitializer" })
public class Product implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column
    private Integer id;//ID
    @Column
    private String title;//标题
    @Column
    private Double marketPrice;//市场价
    @Column
    private Double shopPrice;//商城售价
    @Column
    private String image;//图片
    @Column(name = "`desc`")
    private String desc;//描述
    @Column
    private Integer isHot;//热门产品
    @Column
    private Integer csid;//类别ID
    @Column
    private Date pdate;//上架日期
    @Transient
    private Classification categorySec;
}