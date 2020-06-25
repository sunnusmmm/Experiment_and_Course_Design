package com.nhy.demo.mall.entity;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.persistence.*;
import java.io.Serializable;

/**
 * 订单项
 */
@Entity
@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
@Table(name = "order_item")
public class OrderItem implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column
    private Integer id;//ID
    @Column
    private Integer orderId;//订单号
    @Column
    private Integer productId;//商品ID
    @Column
    private Integer count;//数量
    @Column
    private Double subTotal;//总价

    @Transient
    private Product product;
}