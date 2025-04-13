import React, { useState } from 'react';

function Calculator() {
  const [value, setValue] = useState('');

  const handleClick = (v) => {
    if (v === '=') {
      try {
        setValue(eval(value));
      } catch {
        setValue('Erro');
      }
    } else if (v === 'C') {
      setValue('');
    } else {
      setValue(value + v);
    }
  };

  const buttons = ['7','8','9','/','4','5','6','*','1','2','3','-','0','.','=','+','C'];

  return (
    <div>
      <h2>Calculadora</h2>
      <input value={value} readOnly />
      <div style={{ display: 'grid', gridTemplateColumns: 'repeat(4, 60px)' }}>
        {buttons.map((b) => (
          <button key={b} onClick={() => handleClick(b)}>{b}</button>
        ))}
      </div>
    </div>
  );
}

export default Calculator;
