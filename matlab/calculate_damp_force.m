function [F] = calculate_damp_force(velocity)

cd = 2;
F = -cd * velocity;

end

