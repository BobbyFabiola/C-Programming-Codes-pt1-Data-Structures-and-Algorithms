# My-First-Hash-Table
My FIrst Hashing Hands-on

What's an ADT Dictionary?
    little to no need for UID operations; focuses on maintaining a set of "current" objects/elements; occasional element presence checks

What's a Hash Table?
    Hash Table/Hash Map / File Cabinet; mapping keys to specific locations within an array; enables data retrieval and storage.

    - dictionary implementation, caches, database indexing
    - collision management & appropiate hash functions for optimal performance

Hashing / Hash Function 
    The process of converting input data into a fixed-sized hash code/unique key that represents an index in the table; used for data retrieval, integrity checks, and other applications.

    Two forms of Hashing:
    1. Open/External Hashing (closed addressing)
        Allows sets in potentially unlimited space, no size limits; an array in which each index is able to accomodate an unlimited number of elements.
    2. Closed/Internal Hashing (open addressing)
        Fixed storage space, imposes size limits; an array where each index accomodates one element.

 OPEN HASHING (closed addressing)
    Implementations: Array (of pointers) and Bit Vector

    Finite number of buckers or classes; every bucket has its respective hash value; goal is evenly sized buckets to ensure efficient dictionary operations.

Simple Hash() Function
    Adding all digits of an id number then get the modulo result from its value to the number of elements in the array or array size.

Functions for Open Hashing:
    initialize()
    hash()
    isMember()
    insert()
    delete()
    search()