import React, { useState } from 'react';

function ClickCounter() {
  const [count, setCount] = useState(0);
  return (
    <div>
      <h2>Contador de Cliques</h2>
      <p>Você clicou {count} vezes</p>
      <button onClick={() => setCount(count + 1)}>Clique aqui</button>
    </div>
  );
}

export default ClickCounter;
