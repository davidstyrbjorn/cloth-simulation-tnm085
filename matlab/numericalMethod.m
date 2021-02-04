function [velocity_return, position_return] = numericalMethod(velocity,position,step_size,acceleration,method)

switch method
   case 'euler' %Eulers method
      velocity_return = velocity + acceleration*step_size;
      position_return = position + velocity_return*step_size;
    
    case 'runge-kutta' %Runge-Kutta method
    
        velocity_return = velocity + acceleration*step_size;
    
        %Anonymous fuction
        F_xy=@(x,y) x+y*step_size;
   
        k1 = F_xy(velocity_return,position);
        k2 = F_xy(velocity_return+0.5*step_size,position+0.5*step_size*k1);
        k3 = F_xy(velocity_return+0.5*step_size,(position+0.5*step_size*k2));
        k4 = F_xy(velocity_return+step_size, position+k3*step_size);
    
        position_return = position+ (1/6)*(k1+2*k2+2*k3+k4)*step_size;
   otherwise
    disp("Error, Method not found")
end

end

