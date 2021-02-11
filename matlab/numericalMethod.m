function [velocity_return, position_return] = numericalMethod(velocity, position, force_w_damp, mass, step_size, acceleration, method)

switch method
   case 'euler' %Eulers method
      velocity_return = velocity + acceleration*step_size;
      position_return = position + velocity_return*step_size;
    
    case 'runge-kutta' %Runge-Kutta method
    
        k1 = step_size * ((force_w_damp + calculate_damp_force(velocity))/mass);
        k2 = step_size * ((force_w_damp + calculate_damp_force(velocity + (k1/2) ))/mass);
        k3 = step_size * ((force_w_damp + calculate_damp_force(velocity + (k2/2) ))/mass);
        k4 = step_size * ((force_w_damp + calculate_damp_force(velocity + (k3) ))/mass);
        
        velocity_return = velocity + (k1 + 2*k2 + 2*k3 + k4)/6; % poggers 
        position_return = position + velocity_return * step_size;
end

end

