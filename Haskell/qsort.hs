qsort [] = []
qsort (x:xs) = qsort(less) ++ [x] ++ qsort(greater)
                 where less = [l | l <- xs, l <= x]
                       greater = [g | g <- xs, g > x]
