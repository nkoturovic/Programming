-- Factorial implementation
factorial :: Integer -> Integer
factorial n = if n <= 1 then 1 
              else n * factorial (n-1)

-- Factorial0 implementation
factorial0 :: Integer -> Integer
factorial0 n 
  | n < 2 = 1
  | otherwise = n * factorial0 (n-1)

-- Factorial implementation 1
factorial' :: Integer -> Integer
factorial' 0 = 1
factorial' n = n * factorial' (n-1)

-- Factorial implementation 2
factorial'' :: Integer -> Integer
factorial'' n = foldl (*) 1 [1..n] 

-- Factorial implementation 3
factorial''' :: Integer -> Integer
factorial''' n = product[1..n]

-- Elements of Haronic series
harm_series :: (Eq n, Fractional n) => n -> n
harm_series 1 = 1.0
harm_series n = harm_series(n-1) + 1/n
