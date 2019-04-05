
trougao :: Int -> [(Int, Int, Int)]
trougao n = [(x, y, z) | x <- [1..n], y <- [1..n], z <- [1..n], x +y > z, y + z > x, x + z > y]

raznostranicni :: [(Int, Int, Int)] -> Int
raznostranicni [] = 0
raznostranicni ((x,y,z):xs) = if x /= y && y /= z && x /= z then 1 + raznostranicni(xs) else raznostranicni(xs) 
