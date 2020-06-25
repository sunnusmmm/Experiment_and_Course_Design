package com.nhy.demo.mall.entity;

import lombok.*;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Data
@Builder
@NoArgsConstructor
@AllArgsConstructor
@Table(name = "shop_car")
public class ShopCartItem implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column
    private Integer id;//ID
    @Column
    private Integer userid;//所属用户ID
    @Column
    private Integer productid;//商品ID
}
