function searchsortedstart(sortedArray, x)
    left = 1
    right = length(sortedArray)
    mid = 0
    index = -1
    while(left<=right)
        mid = div(left+right, 2)
        if(sortedArray[mid] == x) 
            index = mid
            break
        end
        if(sortedArray[mid] > x)
            right = mid-1
        else
            left = mid+1
        end
    end
    if(index == -1) 
        if(x>sortedArray[mid]) index = mid+1
        else index = mid end
    else
        if((index-1 == 0) || sortedArray[index-1]!=x)
            return index
        else
            left = 1
            right = index
            mid = 0
            index = -1
            while(left<=right)
                mid = div(left+right, 2)
                if((mid==1 && sortedArray[mid]==x) || (sortedArray[mid]==x && sortedArray[mid-1]!=x)) 
                    index = mid
                    break
                end
                if(sortedArray[mid] == x)
                    right = mid-1
                else
                    left = mid+1
                end
            end
        end
    end
    return index
end

function searchsortedlast(sortedArray, x)
    left = 1
    right = length(sortedArray)
    mid = 0
    index = -1
    while(left<=right)
        mid = div(left+right, 2)
        if(sortedArray[mid] == x) 
            index = mid
            break
        end
        if(sortedArray[mid] > x)
            right = mid-1
        else
            left = mid+1
        end
    end
    if(index == -1) 
        if(x>sortedArray[mid]) index = mid
        else index = mid-1 end
    else
        if((index+1 > length(sortedArray)) || sortedArray[index+1]!=x)
            return index
        else
            left = index
            right = length(sortedArray)
            mid = 0
            index = -1
            while(left<=right)
                mid = div(left+right, 2)
                if((mid==length(sortedArray) && sortedArray[mid]==x) || (sortedArray[mid]==x && sortedArray[mid+1]!=x)) 
                    index = mid
                    break
                end
                if(sortedArray[mid] == x)
                    left = mid+1
                else
                    right = mid-1
                end
            end
        end
    end
    return index
end

function searchSorted(sortedArray, x)
    return string(searchsortedstart(sortedArray, x),":",searchsortedlast(sortedArray, x))
end