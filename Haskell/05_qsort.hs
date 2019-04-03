{-- Quick sort 1 --}
qsort :: (Ord a) => [a] -> [a]    
qsort [] = []
qsort (x:xs) = qsort(smaller) ++ [x] ++ qsort(bigger)
                 where smaller = [l | l <- xs, l <= x]
                       bigger = [g | g <- xs, g > x]

{-- Quick sort 2 --}
qsort' :: (Ord a) => [a] -> [a]    
qsort' [] = []    
qsort' (x:xs) =     
    let smaller = qsort' (filter (<=x) xs)  
        bigger = qsort' (filter (>x) xs)   
    in  smaller ++ [x] ++ bigger 
