function [value] = absolute_vector(p, q)
% p is 1x1x2, q is 1x1x2

p_x = p(1,1,1);
p_y = p(1,1,2);
q_x = q(1,1,1);
q_y = q(1,1,2);

value = sqrt ( (p_x-q_x)^2 + (p_y-q_y)^2 );

end

