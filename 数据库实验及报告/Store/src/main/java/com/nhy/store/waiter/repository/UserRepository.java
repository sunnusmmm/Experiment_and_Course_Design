package com.nhy.store.waiter.repository;


import com.nhy.store.waiter.model.User;
import org.springframework.data.jpa.repository.JpaRepository;

public interface UserRepository extends JpaRepository<User, Long> {
    public User findUserByIdAndUsername(Long id, String name);

    public User findByUsernameAndPassword(String name, String password);

    public User findByUsername(String name);
}
