clear all;

% Declare constant
K = 3;
L0 = 0.1;
m = 0.1;

step_size = 0.1;
t_end = 25;
size_t = t_end/step_size; 

number_of_points = 16*16;
number_of_points_side = sqrt(number_of_points);

v = zeros(size_t, number_of_points, 2);
p = zeros(size_t, number_of_points, 2);

p = zeros(1,1,2);
q = zeros(1,1,2);

z = 1;
h = 1;    
for j = 1:number_of_points
    
    p(1,j,1) = z*L0*0.95;
    p(1,j,2) = h*L0*0.95;
    
    % Grid border checking, z = x-axis, h = y-axis
    z = z + 1;
    if z == number_of_points_side+1
       z = 1; 
       h = h + 1;
    end
end

i = 2;
for t = step_size:step_size:t_end
   
    z = 1;
    h = 1;     
    for j = 1:number_of_points  
        
        if( (z == 1 || z == number_of_points_side) && h == number_of_points_side)            
            a = zeros(1,1,2);
            v(i,j,:) = v(i-1,j,:) + a*step_size;
            p(i,j,:) = p(i-1,j,:) + v(i,j,:)*step_size;  
        else
            F_spring_tot = zeros(1,1,2);   
               
            % Structural 
            if(z ~= 1)
                q = p(i-1, j-1, :); % Point to the left
                F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
            end
            if(z ~= number_of_points_side)
                q = p(i-1, j+1, :); % Point to the right
                F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
            end

            if(h ~= 1)
                q = p(i-1, j-number_of_points_side, :); % Point above
                F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
            end
            if(h ~= number_of_points_side)
                q = p(i-1, j+number_of_points_side, :); % Point under
                F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
            end
            % Shear
            if(z ~= 1) % Inte till vänster
                if(h ~= 1) 
                    q = p(i-1, j-number_of_points_side-1, :);
                    F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
                end
                if(h ~= number_of_points_side)
                    q = p(i-1, j+number_of_points_side-1, :);
                    F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
                end
            end
            if(z ~= number_of_points_side)
                if(h ~= 1) 
                    q = p(i-1, j-number_of_points_side+1, :);
                    F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
                end
                if(h ~= number_of_points_side)
                    q = p(i-1, j+number_of_points_side+1, :);
                    F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
                end
            end
            % Flexion (bend)
            if(z-2 >= 1)
                q = p(i-1, j-2, :); % Point to the left*2
                F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
            end
            if(z+2 <= number_of_points_side)
                q = p(i-1, j+2, :); % Point to the right*2
                F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
            end

            if(h-2 >= 1)
                q = p(i-1, j-number_of_points_side*2, :); % Point above*2
                F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
            end
            if(h+2 <= number_of_points_side)
                q = p(i-1, j+number_of_points_side*2, :); % Point under*2
                F_spring_tot = F_spring_tot + calculate_spring_force(p(i-1,j,:), q, K, L0);
            end

            % Calculate Fmg and Fdamp 
            g = zeros(1,1,2);
            %g(1,1,1) = -1;
            g(1,1,2) = -9.82;
            
            Fdamp = zeros(1,1,2);
            Fdamp(1,1,:) = calculate_damp_force(v(i-1, j, :));
            
            Ftot = F_spring_tot + m*g + Fdamp;
            a = Ftot/m;
            
            % Perform numerical method and insert into v and p
            [v(i,j,:), p(i,j,:)] = numericalMethod(v(i-1,j,:), p(i-1,j,:), Ftot-Fdamp, m, step_size, a, 'runge-kutta'); 
        end
        
        % Grid border checking, z = x-axis, h = y-axis
        z = z + 1;
        if z == number_of_points_side+1
           z = 1; 
           h = h + 1;
        end
    end

    i = i +1;
end

i = 1;
for t = step_size:step_size:t_end

    scatter(p(i,:,1), p(i,:,2), 'filled');
    drawnow;
    
    i = i + 1;
end