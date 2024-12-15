from decimal import Decimal



def func(n, x):
    if n == 1:
        return 6 * x ** 5
    else:
        return x ** Decimal(1 / 30) * (1 + x ** 2) ** Decimal(0.5)



def derivative(n, x):
    if n == 1:
        return 720 * x
    else:
        return 0



def integral(func_num, pr, a, b, check):
    print("n\t\tk_d\t\t\t\t\t\t\t\td_точное\t\t\t\t\t\td_Рунге\t\t\t\t\t\t\t\t d_теор")
    print("-" * spaces)



    J_old = J_old_old = Decimal("0")
    K_d = d_pr = K_Run = Decimal("0")



    count_segments = 1
    while count_segments < 66000:
        h = Decimal((b - a) / count_segments)



        array_x = [0 for _ in range(count_segments + 1)]
        array_y = [0 for _ in range(count_segments + 1)]

        for i in range(count_segments + 1):
            array_x[i] = h * i + a
            array_y[i] = func(func_num, array_x[i])



        sum_x_1 = sum_x_2 = Decimal("0")

        for i in range(count_segments):
            if i != 0: sum_x_1 += array_y[i]
            sum_x_2 += func(func_num, array_x[i] + h / 2)



        J = (h / 6) * (array_y[0] + array_y[count_segments] + 2 * sum_x_1 + 4 * sum_x_2)



        if J_old_old != 0:
            K_d = (J_old - J_old_old) / (J - J_old)

        if check:
            d_pr = pr - J

        if J_old != 0:
            K_Run = (J - J_old) / (16 - 1)

        d_th = Decimal("0")
        if check:
            for i in range(count_segments + 1):
                if derivative(func_num, array_x[i]) > d_th:
                    d_th = derivative(func_num, array_x[i])
        d_th *= h ** 4 / 2880

        J_old_old = J_old
        J_old = J



        if count_segments < 100: print(count_segments, "\t\t", end='')
        else:                    print(count_segments, "\t",   end='')

        if   K_d == 0:                       print("-", "\t\t\t\t\t\t\t\t", end='')
        elif check and count_segments < 100: print(K_d, "\t\t\t\t\t\t\t\t", end='')
        else:                                print(K_d, "\t",               end='')

        if   check and count_segments < 30:    print(d_pr, "\t",               end='')
        elif check and count_segments < 500:   print(d_pr, "\t\t",             end='')
        elif check and count_segments < 4000:  print(d_pr, "\t\t\t",           end='')
        elif check and count_segments < 60000: print(d_pr, "\t\t\t\t",         end='')
        elif check and count_segments > 60000: print(d_pr, "\t\t\t\t\t",       end='')
        elif check and count_segments < 512:   print(d_pr, "\t",               end='')
        else:                                  print("-",  "\t\t\t\t\t\t\t\t", end='')

        if K_Run == 0: print("-",   end='')
        else:          print(K_Run, end='')

        if       check and len(str(K_Run)) == 1:  print("\t\t\t\t\t\t\t\t\t", d_th)
        elif not check and len(str(K_Run)) == 1:  print("\t\t\t\t\t\t\t\t\t", "-")
        elif     check and len(str(K_Run)) >= 32: print("\t",                 d_th)
        elif not check and len(str(K_Run)) >= 32: print("\t",                 "-")
        elif     check and len(str(K_Run)) >= 28: print("\t\t",               d_th)
        elif not check and len(str(K_Run)) >= 28: print("\t\t",               "-")
        elif     check and len(str(K_Run)) >= 24: print("\t\t\t",             d_th)
        elif not check and len(str(K_Run)) >= 24: print("\t\t\t",             "-")
        elif     check and len(str(K_Run)) >= 20: print("\t\t\t\t",           d_th)
        elif not check and len(str(K_Run)) >= 20: print("\t\t\t\t",           "-")
        elif     check and len(str(K_Run)) >= 16: print("\t\t\t\t\t",         d_th)
        else                                    : print("\t\t\t\t\t",         "-")



        count_segments *= 2



spaces = 150



print("-" * spaces, "\nФункция y = 6 * x^5 на отрезке [0, 1]")
print("-" * spaces)
integral(1, 1, 0, 1, True)



print("-" * spaces, "\n")
print("-" * spaces, "\nФункция y = x^(1/m) * (1+x^2)^(1/2) на отрезке [0, 1.5]")
print("-" * spaces)
integral(2, 0, 0, 1.5, False)



print("-" * spaces, "\n")
print("-" * spaces, "\nФункция y = x^(1/m) * (1+x^2)^(1/2) на отрезке [0.001, 1.5]")
print("-" * spaces)
integral(2, 0, Decimal("0.001"), Decimal("1.5"), False)
print("-" * spaces)
