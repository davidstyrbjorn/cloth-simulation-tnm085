function [F] = calculate_spring_force(p, q, K, L0)

% p is a 1x1x2
% q is a 1x1x2

F = zeros(1,1,2);

a = absolute_vector(p,q);
F(1,1,:) = K*(L0 - a)*( (p-q)/a );

end

