
# 問題描述

某一城市欲建立都會網路，以使每一城市均可連線到其他各城市(可能直接連線或透過其他的城市間接連線)。假設任兩個城市之間的佈線成本為已知(有些城市之間已知無法佈線，其佈線成本可視為無限大)；每一條網路線均為雙向傳送。請寫一程式，印出哪些城市之間需要施工佈線，以找出此城市使用最低成本完成都會網路之佈線架構。

## 輸入格式：

第一列有兩個正整數n及m，其中n代表城市個數(n<=10)，m代表有m個可能的佈線連結兩城市。
第二列有n個字串，代表n個城市代表(代碼最多5個字元)。其後有m列，每一列之資料依序為兩城市代碼，及連接此兩城市之佈線成本。各項資料之間以一個空白分隔；佈線成本為一正整數。

## 輸出格式：

印出二列。第一列為佈線架構，印出數組資料，每一組資料為兩個城市代碼，代表此兩個城市需要施工佈線，每一組資料包含在一對括號之中。第二列為佈線總成本。各項資料之間以一個空白分隔。

## 輸入範例：

6 9
C1 C2 C3 C4 C5 C6
C 1 C 2 1
C 1 C 4 7
C 2 C 3 3
C 2 C 4 6
C 2 C 5 4
C 3 C 5 5
C 3 C 6 9
C 4 C 5 3
C 5 C 6 8

##輸出範例：

(C 1 C 2)( C 2 C 3)( C 4 C 5)( C 2 C 5)( C 5 C 6)
19

## 解題策略

基礎的 Minimun Spanning Tree，用 Kruskal's algorithm 解 [範例程式](main.cpp)
