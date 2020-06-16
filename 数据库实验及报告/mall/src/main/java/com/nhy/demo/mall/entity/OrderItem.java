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
    private Integer id;
    /**
     * 订单Id
     */
    @Column
    private Integer orderId;
    /**
     * 商品Id
     */
    @Column
    private Integer productId;
    /**
     * 数量
     */
    @Column
    private Integer count;
    /**
     * 总价
     */
    @Column
    private Double subTotal;

    @Transient
    private Product product;
}