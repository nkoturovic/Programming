factorial :: Integer -> Integer
factorial n = if n <= 1 then 1 
		else n * factorial (n-1)

factorial1 :: Integer -> Integer
factorial1 0 = 1
factorial1 n = n * factorial1 (n-1)

factorial2 :: Integer -> Integer
factorial2 n = foldl (*) 1 [1..n] 

factorial3 :: Integer -> Integer
factorial3 n = product[1..n]
